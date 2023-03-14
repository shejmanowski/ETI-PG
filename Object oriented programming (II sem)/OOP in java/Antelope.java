import java.awt.*;

public class Antelope extends Animal {
    public Antelope(Position position, World world){
        super("Antelope", 4, 4, new Color(229, 181, 90, 255), position, world);
    }

    @Override
    public void action(){
        Position desiredPosition = getDesiredPosition(2);
        if (world.isEmpty(desiredPosition)) {
            move(desiredPosition);
        } else {
            collision(world.getOrganism(desiredPosition));
        }
        updateAge();
    }

    @Override
    public boolean runAway(){
        Position emptyNeighbourField = this.findEmptyNeighbourField();
        if(emptyNeighbourField == null) return false;
        if(world.chanceOfBeingTrue(0.5f)) return false;
        this.setPosition(emptyNeighbourField);
        return true;
    }
}
