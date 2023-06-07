import java.lang.Thread;
import java.lang.Runnable;

public class DigitCountThread extends Thread implements Runnable {

    private int count;
    private String inputText;

    public DigitCountThread(String str) {
        inputText = str;
    }

    public void run() {
        for (int i = 0; i < inputText.length(); i++) {
            char ch = inputText.charAt(i);
            if (ch >= 48 && ch <= 57) {
                count++;
            }
        }
        System.out.println("\n The digit count: " + count);
    }
}
