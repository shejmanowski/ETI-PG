import java.awt.*;

public class Guarana extends Plant {
    public Guarana(Position position, World world){
        super("Guarana", 0,new Color(206, 62, 62, 255), position, world);
    }

    @Override
    public boolean gaveStrengthIncrease() {
        return true;
    }
}
