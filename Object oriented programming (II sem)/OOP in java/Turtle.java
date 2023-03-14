import java.awt.*;

public class Turtle extends Animal {
    public Turtle(Position position, World world){
        super("Turtle", 2, 1,new Color(67, 112, 0, 255), position, world);
    }

    @Override
    public void action(){
        if(world.chanceOfBeingTrue(0.25f)) super.action();
    }

    @Override
    public boolean blockedAttack(Organism other){
        return other.getStrength() < 5;
    }
}
