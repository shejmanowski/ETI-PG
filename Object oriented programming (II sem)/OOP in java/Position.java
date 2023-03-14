import java.io.Serializable;
import java.util.Objects;

public class Position implements Serializable {
    private int x;
    private int y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Position(Position position){
        this.x = position.getX();
        this.y = position.getY();
    }

    public void setPosition(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Position position = (Position) o;
        return x == position.x && y == position.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString(){
        return "(" + x + ", " + y + ")";
    }

    public void moveRight(int dist) {
        x += dist;
    }

    public void moveUp(int dist) {
        y -= dist;
    }

    public void moveLeft(int dist) {
        x -= dist;
    }

    public void moveDown(int dist) {
        y += dist;
    }

    public void moveUpRight(int dist) {
        x += dist;
        y -= dist;
    }

    public void moveDownLeft(int dist) {
        x -= dist;
        y += dist;
    }

    public void moveInGivenDirection(int direction, int dist) {
        switch (direction) {
            case 0 -> moveUp(dist);
            case 1 -> moveRight(dist);
            case 2 -> moveDown(dist);
            case 3 -> moveLeft(dist);
            case 4 -> moveUpRight(dist);
            case 5 -> moveDownLeft(dist);
        }
    }


}
