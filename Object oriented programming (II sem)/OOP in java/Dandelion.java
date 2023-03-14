import java.awt.*;

public class Dandelion extends Plant {
    public Dandelion(Position position, World world){
        super("Dandelion", 0, new Color(255, 209, 39, 255), position, world);
    }

    @Override
    public void action(){
        if(world.chanceOfBeingTrue(0.2f) || world.chanceOfBeingTrue(0.2f) || world.chanceOfBeingTrue(0.2f)) spread();
    }
}
