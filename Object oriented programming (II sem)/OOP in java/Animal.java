import java.awt.*;

public class Animal extends Organism {

    public Animal(String name, int strength, int initiative, Color color, Position position, World world) {
        super(name, strength, initiative, color, position, world);
    }

    @Override
    public void action() {
        Position desiredPosition = getDesiredPosition(1);
        if (world.isEmpty(desiredPosition)) {
            move(desiredPosition);
        } else {
            collision(world.getOrganism(desiredPosition));
        }
        updateAge();
    }

    @Override
    public void move(Position position) {
        this.position = position;
        world.addAnnounce(announcer.move(this, position));
    }

    @Override
    public void collision(Organism other) {
        if (this.getClass() == other.getClass()) {
            reproduce();
        } else {
            fight(other);
        }
    }

    public void reproduce() {
        if (!isSurroundedByItsSpecies()) {
            Position newOrganismPosition;
            do {
                newOrganismPosition = getDesiredPosition(1);
                if (world.isEmpty(newOrganismPosition)) break;
            } while (world.getOrganism(newOrganismPosition).getClass() != this.getClass());
            world.newLivingOrganism(this, newOrganismPosition);
            world.addAnnounce(announcer.reproduction(this));
        }
    }

    public void fight(Organism other) {
        Position desiredPosition = other.getPosition();
        if (other.blockedAttack(this)) return;
        if (other.runAway()) {
            this.move(desiredPosition);
            return;
        }
        if (this.isStrongerOrEqualThen(other)) {
            world.addAnnounce(announcer.death(other, this));
            if (other.gaveStrengthIncrease()) this.increaseStrength(3);
            other.setPositionToNull();
            move(desiredPosition);
        } else {
            world.addAnnounce(announcer.death(this, other));
            this.setPositionToNull();
        }
    }
}
