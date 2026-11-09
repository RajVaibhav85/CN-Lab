import java.util.* ;

public class Hamming {

    public static int[] encode(int[] data){
        int m = data.length;
        int r = 0;
        
        while ((1 << r) < m + r + 1) {
            r++;
        }
        
        int[] encoded = new int[m + r];

        for(int i = 1 , j = 0; i <= m+r ; i++)
            if(i == (1 << j))
                j++;
            else 
                encoded[i-1] = data[i-j-1];

        for(int i = 0 ; i < r ; i++){
            int parityPos = (1 << i);
            int parity = 0;
            for(int j = 1 ; j <= m+r ; j++){
                if((j & parityPos) != 0)
                    parity ^= encoded[j-1];
            }
            encoded[parityPos-1] = parity;
        }

        return encoded;
    }

    public static int[] decode(int[] encoded){
        int m = encoded.length;
        int r = 0;
        
        while ((1 << r) < m + 1) {
            r++;
        }
        
        int errorPos = 0;
        for(int i = 0 ; i < r ; i++){
            int parityPos = (1 << i);
            int parity = 0;
            for(int j = 1 ; j <= m ; j++){
                if((j & parityPos) != 0)
                    parity ^= encoded[j-1];
            }
            if(parity != 0)
                errorPos += parityPos;
        }

        if(errorPos > 0 && errorPos <= m){
            encoded[errorPos-1] ^= 1; // Correct the error
        }

        int[] data = new int[m - r];
        for(int i = 1 , j = 0; i <= m ; i++)
            if(i == (1 << j))
                j++;
            else 
                data[i-j-1] = encoded[i-1];

        return data;
    }
    public static void main(String[] args){
        int[] data = {1, 0, 1, 1};
        int[] encoded = encode(data);
        System.out.println("Encoded: " + Arrays.toString(encoded));
        encoded[2] ^= 1; // Introduce an error
        System.out.println("With error: " + Arrays.toString(encoded));
        int[] decoded = decode(encoded);
        System.out.println("Decoded: " + Arrays.toString(decoded));
    }
}