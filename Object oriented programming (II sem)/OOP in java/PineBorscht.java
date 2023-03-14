import java.awt.*;

public class PineBorscht extends Plant {
    public PineBorscht(Position position, World world){
        super("Pine Borscht", 10, new Color(244, 255, 200, 255),position, world);
    }

    @Override
    public void action(){
        killNeighbourAnimals();
    }

    public void killNeighbourAnimals(){
        int numberOfDirections = 4;
        if(world.getHexMode()) numberOfDirections = 6;
        for(int i = 0; i < numberOfDirections; i++){
            Position myPosition = new Position(position);
            myPosition.moveInGivenDirection(i, 1);
            if(world.getOrganism(myPosition) instanceof Animal) world.getOrganism(myPosition).setPositionToNull();
        }
    }
}
