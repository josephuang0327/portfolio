import java.lang.Thread;

public class isPalindrome extends Thread {

    private boolean check;
    private String inputText;

    public isPalindrome(String str) {
        inputText = str;
    }

    public void run() {
        int i = 0;
        int j = inputText.length() - 1;

        while (i < j) {
            // System.out.println(inputText.charAt(i) + " = " + inputText.charAt(j));
            if (inputText.charAt(i) != inputText.charAt(j)) {
                check = false;
                break;
            }
            i++;
            j--;
            check = true;
        }

        System.out.println("\n Is a palindrome?: " + check);

    }
}
