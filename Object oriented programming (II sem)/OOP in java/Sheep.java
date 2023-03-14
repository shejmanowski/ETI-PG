import java.awt.*;

public class Sheep extends Animal{
    public Sheep(Position position, World world){
        super("Sheep", 4, 4,new Color(108, 108, 108, 255), position, world);
    }
}
