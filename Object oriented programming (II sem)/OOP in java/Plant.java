import java.awt.*;

public class Plant extends Organism {
    public Plant(String name, int strength, Color color, Position position, World world) {
        super(name, strength, 0, color, position, world);
    }

    @Override
    public void action() {
        if (world.chanceOfBeingTrue(0.2f)) spread();
    }

    public void spread() {
        Position desiredPosition = this.getDesiredPosition(1);
        if (world.isEmpty(desiredPosition)) {
            world.addAnnounce(announcer.spreading(this));
            world.newLivingOrganism(this, desiredPosition);
        }
    }
}
