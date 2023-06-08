import java.lang.Thread;

public class upperCount extends Thread {
    private int count;
    private String inputText;

    public upperCount(String str) {
        inputText = str;
    }

    public void run() {

        for (int i = 0; i < inputText.length(); i++) {
            char ch = inputText.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                count++;
            }
        }
        System.out.println("\n The uppercase count: " + count);
    }
}
