import java.awt.*;

public class Wolf extends Animal{
    public Wolf(Position position, World world){
        super("Wolf", 9, 5,new Color(84, 84, 84, 255), position, world);
    }
}
