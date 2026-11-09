"""
Latent Semantic Analysis (LSA) with Truncated SVD.
Libraries: numpy, pandas, matplotlib (+ ast from the standard library to read the file).

Steps
  1. Build a word x document count matrix, then apply log-entropy weighting
  2. Truncated SVD (keep k = 2 concepts) and project the words into 2-D
  3. Find the words closest to a target word using cosine similarity

Run from the 'experiment' folder:  python lsa_svd.py
"""
import ast
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

K = 2              # number of latent concepts to keep
CHUNK_SIZE = 30    # words per "document" (see the note in STEP 0)


# =================================================================== STEP 0
# Read dataset.txt. The file is Python code that looks like:  dataset = [ {...} ]
# so we cut off the "dataset =" part and read the list that follows.
text = open("datasets/dataset.txt").read()
text = text.split("=", 1)[1]
dataset = ast.literal_eval(text)

# NOTE: dataset.txt contains only ONE story (330 words). A word x document matrix
# with a single column cannot be reduced to 2 concepts, so we cut the story's
# word list into small consecutive chunks and treat every chunk as one document.
all_words = dataset[0]["words"]
documents = []
for start in range(0, len(all_words), CHUNK_SIZE):
    documents.append(all_words[start:start + CHUNK_SIZE])
print("Words in story:", len(all_words), "| Documents (chunks):", len(documents))


# =================================================================== STEP 1
def makeDocumentTermMatrix(data):
    """data = list of documents, each document is a list of words.
    Returns a (words x documents) matrix. Entry [i, j] = how many times word i
    appears in document j. Also returns the list of words (row labels)."""
    # 1. collect every different word and give it a row number
    vocab = []
    for doc in data:
        for word in doc:
            if word not in vocab:
                vocab.append(word)
    vocab = sorted(vocab)
    row_of = {}
    for i in range(len(vocab)):
        row_of[vocab[i]] = i

    # 2. count
    matrix = np.zeros((len(vocab), len(data)))
    for j in range(len(data)):
        for word in data[j]:
            matrix[row_of[word], j] += 1
    return matrix, vocab


def logEntropyNormalize(counts):
    """Log-entropy weighting.
        local  L_ij = log(1 + tf_ij)                       (dampens big counts)
        p_ij        = tf_ij / (sum of row i)               (row probabilities)
        global G_i  = 1 + sum_j p_ij * log(p_ij) / log(n)  (1 = word is concentrated in
                                                            few documents, 0 = spread evenly)
        result_ij   = L_ij * G_i
    """
    n_docs = counts.shape[1]

    local = np.log(1 + counts)

    row_sums = counts.sum(axis=1, keepdims=True)
    p = counts / row_sums

    # p * log(p) is 0 when p = 0 (we avoid log(0) by replacing 0 with 1, since log(1) = 0)
    p_safe = np.where(p > 0, p, 1)
    entropy_term = (p * np.log(p_safe)).sum(axis=1)
    global_weight = 1 + entropy_term / np.log(n_docs)

    return local * global_weight.reshape(-1, 1)


counts, vocab = makeDocumentTermMatrix(documents)
normalized = logEntropyNormalize(counts)
word_index = {}
for i in range(len(vocab)):
    word_index[vocab[i]] = i

print("Count matrix (words x documents):", counts.shape)
print(pd.DataFrame(counts, index=vocab).head(8).astype(int))
print("\nNormalized matrix, first rows:")
print(pd.DataFrame(normalized, index=vocab).head(8).round(3))


# =================================================================== STEP 2
# Full SVD:  normalized = U @ diag(S) @ Vt
# ALTERNATIVE: scipy.sparse.linalg.svds(normalized, k=2) gives only the top k directly
U, S, Vt = np.linalg.svd(normalized, full_matrices=False)

# keep only the k strongest concepts (this is the "truncation")
U_k = U[:, :K]          # words x k      (how much each word belongs to each concept)
S_k = S[:K]             # k              (strength of each concept)
Vt_k = Vt[:K, :]        # k x documents  (how much each document belongs to each concept)

print("\nU_k shape :", U_k.shape)
print("S_k       :", S_k.round(3))
print("Vt_k shape:", Vt_k.shape)
print("Share of total variance kept by the", K, "concepts:",
      round((S_k ** 2).sum() / (S ** 2).sum() * 100, 1), "%")

# Project the words into the concept space:  (words x docs) @ (docs x k) = (words x k)
word_coords = normalized @ Vt_k.T
# Same result as U_k * S_k  (a handy check):
print("Check  normalized @ V  ==  U * S :", np.allclose(word_coords, U_k * S_k))


# =================================================================== STEP 3
def cosine_similarity(a, b):
    """cos(a, b) = (a . b) / (|a| * |b|)"""
    length_a = np.sqrt((a * a).sum())
    length_b = np.sqrt((b * b).sum())
    if length_a == 0 or length_b == 0:
        return 0.0
    return (a * b).sum() / (length_a * length_b)


def find_closest_words(target_word, top_n=3):
    if target_word not in word_index:
        print("'" + target_word + "' is not in the vocabulary.")
        return None
    target_vector = word_coords[word_index[target_word]]

    scores = []
    for word in vocab:
        if word != target_word:
            similarity = cosine_similarity(target_vector, word_coords[word_index[word]])
            scores.append((word, similarity))

    scores.sort(key=lambda pair: pair[1], reverse=True)       # highest similarity first
    return pd.DataFrame(scores[:top_n], columns=["word", "cosine_similarity"])


print("\n==================== Closest words ====================")
# "machine" and "data" are not in this news story, so a few words that are in it are tried too
for target in ["machine", "data", "austerity", "police", "debt"]:
    result = find_closest_words(target)
    if result is not None:
        print("\nTop 3 closest to '" + target + "':")
        print(result.round(4).to_string(index=False))


# =================================================================== PLOT
# All words in the 2-D concept space; the target and its 3 neighbours are highlighted
target = "austerity"
neighbours = list(find_closest_words(target)["word"])

plt.figure(figsize=(8, 6))
plt.scatter(word_coords[:, 0], word_coords[:, 1], color="lightgray", s=15)
for word in [target] + neighbours:
    x, y = word_coords[word_index[word]]
    colour = "red" if word == target else "blue"
    plt.scatter(x, y, color=colour, s=50)
    plt.annotate(word, (x, y), textcoords="offset points", xytext=(5, 5))
plt.axhline(0, color="black", linewidth=0.5)
plt.axvline(0, color="black", linewidth=0.5)
plt.xlabel("Concept 1")
plt.ylabel("Concept 2")
plt.title("Words in the 2-D LSA concept space (red = target, blue = closest words)")
plt.savefig("lsa_words.png", dpi=120)
plt.show()
