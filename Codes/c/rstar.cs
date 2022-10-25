using System;
// you can also use other imports, for example:
// using System.Collections.Generic;

// you can write to stdout for debugging purposes, e.g.
// Console.WriteLine("this is a debug message");

class Solution {
    public int solution(int N, int K) {
        // write your code in C# 6.0 with .NET 4.7 (Mono 6.12)
        int[] digits = new int[3];
        string N_s = N.ToString();
        char[] N_charArray = N_s.ToCharArray();

        for (int i = 0; i < 3; i++){
            digits[i] = N_charArray[i] - '0';
        }

        for (int i = 0; i < 3; i++){
            if(digits[i] < 9 && K >= (9 - digits[i])){
                K = K - (9 - digits[i]);

                digits[i] = 9;
            }
            else if (digits[i] < 9 && K > 0) {
                digits[i] += K;
                K = 0;
            }
        }

        int result = 0;
        int multiplier = 100;

        for(int i = 0; i < 3; i++){
            result += digits[i]*multiplier;
            multiplier /= 10;
        }
        return result;
    }
}
