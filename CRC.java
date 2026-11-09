import java.util.*;
import java.io.*;

public class CRC {
    public static String xorDivision(String dividend, String divisor) {
        int dividendLen = dividend.length();
        int divisorLen = divisor.length();
        StringBuilder dividendArr = new StringBuilder(dividend);

        for (int i = 0; i <= dividendLen - divisorLen; i++) {
            if (dividendArr.charAt(i) == '1') {
                for (int j = 0; j < divisorLen; j++) {
                    dividendArr.setCharAt(i + j, (dividendArr.charAt(i + j) == divisor.charAt(j)) ? '0' : '1');
                }
            }
        }
        return dividendArr.substring(dividendLen - divisorLen + 1);
    }

    public static void main(String[] args) {
        String data = "11010011";
        String divisor = "1001";
        String remainder = xorDivision(data, divisor);
        System.out.println("Data: " + data);
        System.out.println("Divisor: " + divisor);
        System.out.println("Remainder: " + remainder);
        System.out.println("Encoded Data: " + data + remainder);
        System.out.println("Decoded Data: " + xorDivision(data + remainder, divisor));

        long time = System.currentTimeMillis();
        long time2 = System.nanoTime();
        System.out.println("Time taken: " + (System.currentTimeMillis() - time) + " ms");
        System.out.println("Time taken: " + (System.nanoTime() - time2) + " ns");
    }
}
