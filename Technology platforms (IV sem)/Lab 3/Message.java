import java.io.Serializable;

public class Message implements Serializable {
    private int number;
    private String content;
    static final long serialVersionUID = 0;

    public Message(int number, String content){
        this.number = number;
        this.content = content;
    }

    @Override
    public String toString() {
        return "Message{" +
                "number=" + number +
                ", content='" + content + '\'' +
                '}';
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
