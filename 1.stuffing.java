import java.util.*;
import java.io.*;

class Stuffing {

    public static String bitStuff(String s) {
        int count = 0;
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            result.append(c);
            if (c == '1') count++;
            else count = 0;
            if (count == 5) {
                result.append('0');
                count = 0;
            }
        }
        return result.toString();
    }

    public static String bitUnstuff(String s) {
        int count = 0;
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            result.append(c);
            if (c == '1') count++;
            else count = 0;
            if (count == 5) {
                i++; // skip the stuffed 0
                count = 0;
            }
        }
        return result.toString();
    }

    public static String byteStuff(String s) {
        StringBuilder result = new StringBuilder();
        String flag = "01111110", escape = "01111101";
        for (int i = 0; i < s.length(); i += 8) {
            String byteStr = s.substring(i, Math.min(i + 8, s.length()));
            if (byteStr.equals(flag) || byteStr.equals(escape)) {
                result.append(escape);
            }
            result.append(byteStr);
        }
        return result.toString();
    }

    public static String byteUnstuff(String s) {
        StringBuilder result = new StringBuilder();
        String escape = "01111101";
        for (int i = 0; i < s.length(); i += 8) {
            String byteStr = s.substring(i, Math.min(i + 8, s.length()));
            if (byteStr.equals(escape) && i + 8 < s.length()) {
                i += 8;
                byteStr = s.substring(i, Math.min(i + 8, s.length()));
            }
            result.append(byteStr);
        }
        return result.toString();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        System.out.println("Original: " + input);
        System.out.println("After Byte Stuffing: " + byteStuff(input));
        System.out.println("After Byte Unstuffing: " + byteUnstuff(byteStuff(input)));
        System.out.println("After Bit Stuffing: " + bitStuff(input));
        System.out.println("After Bit Unstuffing: " + bitUnstuff(bitStuff(input)));
    }
}