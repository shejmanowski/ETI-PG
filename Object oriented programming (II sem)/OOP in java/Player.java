import java.awt.*;
import java.io.Serializable;

public class Player extends Animal {
    private int desiredDirection;
    private int abilityCooldown;
    private int moveRange;
    public Player(Position position, World world){
        super("Player", 5, 4, new Color(0,0,0), position, world);
        desiredDirection = -1;
        abilityCooldown = 0;
        moveRange = 1;
    }

    public void action(){
        Position desiredPosition = new Position(position);
        determinateMoveRange();
        desiredPosition.moveInGivenDirection(desiredDirection, moveRange);
        if (world.isEmpty(desiredPosition)) {
            move(desiredPosition);
        } else {
            collision(world.getOrganism(desiredPosition));
        }
        updateAge();
        updateCooldown();
    }

    public void setDesiredDirection(int direction){
        desiredDirection = direction;
    }

    public void activateAbility(){
        if (abilityCooldown == 0) abilityCooldown = 5;
    }

    public void determinateMoveRange() {
        if (abilityCooldown > 2 || (abilityCooldown > 0 && world.chanceOfBeingTrue(0.5f))) moveRange = 2;
        else moveRange = 1;
    }

    private void updateCooldown(){
        if(abilityCooldown > 0) abilityCooldown--;
    }
}
