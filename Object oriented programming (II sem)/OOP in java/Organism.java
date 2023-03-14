import java.awt.*;
import java.io.Serializable;
import java.util.Random;

public class Organism implements Serializable {
    private final String name;
    private int strength;
    private final int initiative;
    private int age;
    private final Color color;
    protected Position position;
    protected World world;
    protected Announcer announcer = new Announcer();

    public Organism(String name, int strength, int initiative, Color color, Position position, World world) {
        this.name = name;
        this.strength = strength;
        this.initiative = initiative;
        this.color = color;
        this.position = position;
        this.world = world;
        age = 0;
    }

    public String getName() {
        return name;
    }

    public int getStrength() {
        return strength;
    }

    public int getInitiative() {
        return initiative;
    }

    public Color getColor(){return color;}

    public int getAge() {
        return age;
    }

    public Position getPosition() {
        return position;
    }

    @Override
    public String toString() {
        return name + position.toString();
    }

    public void updateAge() {
        age++;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public void increaseStrength(int value){
        strength += value;
    }

    public void action() {
    }

    ;

    public void collision(Organism other) {
    }

    ;

    public void move(Position position) {
    }

    ;

    public Position getDesiredPosition(int range) {
        Random rand = new Random();
        Position desiredPosition;
        int randDirection;
        do {
            desiredPosition = new Position(position);
            if (world.getHexMode()) randDirection = rand.nextInt(6);
            else randDirection = rand.nextInt(4);
            desiredPosition.moveInGivenDirection(randDirection, range);
        } while (!world.isValid(desiredPosition));
        return desiredPosition;
    }

    public boolean isStrongerOrEqualThen(Organism other) {
        return this.strength > other.getStrength();
    }

    public boolean isSurroundedByItsSpecies() {
        int numberOfDirections = 4;
        if (world.getHexMode()) numberOfDirections = 6;

        for (int i = 0; i < numberOfDirections; i++) {
            Position neighbourPosition = new Position(this.getPosition());
            neighbourPosition.moveInGivenDirection(i, 1);
            if (!world.isValid(neighbourPosition)) continue;
            if (world.isEmpty(neighbourPosition)) return false;
            if (world.getOrganism(neighbourPosition).getClass() != this.getClass()) return false;
        }
        return true;
    }

    public Position findEmptyNeighbourField(){
        int directionsNumber = 4;
        if(world.getHexMode()) directionsNumber = 6;
        for(int i = 0; i < directionsNumber; i++){
            Position neighbourPosition = new Position(this.getPosition());
            neighbourPosition.moveInGivenDirection(i, 1);
            if (world.isValid(neighbourPosition) && world.isEmpty(neighbourPosition)) {
                return neighbourPosition;
            }
        }
        return null;
    }

    public boolean blockedAttack(Organism other){
        return false;
    }

    public boolean runAway(){
        return false;
    }

    public boolean gaveStrengthIncrease(){
        return false;
    }

    public void setPositionToNull(){
        this.position = null;
    }
}
