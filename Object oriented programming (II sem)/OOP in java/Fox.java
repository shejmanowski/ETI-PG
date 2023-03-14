import java.awt.*;

public class Fox extends Animal{
    public Fox(Position position, World world){
        super("Fox", 3, 7,new Color(255, 152, 0, 255), position, world);
    }

    @Override
    public void action(){
        Position desiredPosition = getDesiredPosition(1);
        if (world.isEmpty(desiredPosition)) {
            move(desiredPosition);
        } else if (isStrongerOrEqualThen(world.getOrganism(desiredPosition))) {
            collision(world.getOrganism(desiredPosition));
        }
    }
}
