import java.io.*;
import java.util.*;

public class World implements Serializable {
    private final int sizeX;
    private final int sizeY;
    private int round;
    private final boolean hexMode;
    private final float startingPopulationDensity;
    private final List<Organism> livingOrganisms;
    private final ArrayList<String> announces;
    private Player player;


    public World(int sizeX, int sizeY, boolean hexMode) {
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        this.hexMode = hexMode;
        livingOrganisms = new ArrayList<>();
        announces = new ArrayList<>();
        round = 0;
        startingPopulationDensity = 0.2f;
        generateWorld();
    }

    public int getSizeX() {
        return sizeX;
    }

    public int getSizeY() {
        return sizeY;
    }

    public Player getPlayer(){
        return player;
    }

    public ArrayList<String> getAnnounces(){
        return announces;
    }

    public boolean getHexMode() {
        return hexMode;
    }

    public void generateWorld() {
        spawnPlayer();
        spawnOrganisms();
    }

    private void spawnOrganisms(){
        Random random = new Random();
        List<String> allOrganismsNames = new ArrayList<>(Arrays.asList("Wolf", "Sheep", "Fox", "Turtle",
                "Antelope", "Grass", "Dandelion", "Guarana", "Wolfberries", "PineBorscht"));
        int fields = sizeX * sizeY;
        int numberOfOrganisms = (int) (startingPopulationDensity * fields);
        for(int i = 0; i < numberOfOrganisms; i++){
            Position newOrganismPosition;
            int x, y;
            do {
                x = random.nextInt(sizeX);
                y = random.nextInt(sizeY);
                newOrganismPosition = new Position(x, y);
            }   while(!isEmpty(newOrganismPosition));

            String organismName = allOrganismsNames.get(random.nextInt(allOrganismsNames.size()));
            newLivingOrganism(organismName, newOrganismPosition);
        }
    }

    public void nextRound() {
        sortOrganisms();
        for (int i = 0; i < livingOrganisms.size(); i++) {
            if(livingOrganisms.get(i).position != null) livingOrganisms.get(i).action();
        }
        updateLivingOrganisms();
        clearAnnounces();
        round++;
    }

    private void sortOrganisms(){
        OrganismComparator oc = new OrganismComparator();
        livingOrganisms.sort(oc);
    }

    public boolean isValid(Position position) {
        return position.getX() >= 0 && position.getX() < sizeX && position.getY() >= 0 && position.getY() < sizeY;
    }

    public boolean isEmpty(Position position) {
        for (Organism livingOrganism : livingOrganisms) {
            if (position.equals(livingOrganism.getPosition())) return false;
        }
        return true;
    }

    public Organism getOrganism(Position position) {
        for (Organism livingOrganism : livingOrganisms) {
            if (position.equals(livingOrganism.getPosition())) return livingOrganism;
        }
        return null;
    }

    public void newLivingOrganism(Organism organism, Position position) {
        Organism newOrganism = null;
        if (organism instanceof Wolf) {
            newOrganism = new Wolf(position, this);
        } else if (organism instanceof Sheep) {
            newOrganism = new Sheep(position, this);
        } else if (organism instanceof Fox) {
            newOrganism = new Fox(position, this);
        } else if (organism instanceof Turtle) {
            newOrganism = new Turtle(position, this);
        } else if (organism instanceof Antelope) {
            newOrganism = new Antelope(position, this);
        } else if (organism instanceof Grass) {
            newOrganism = new Grass(position, this);
        } else if (organism instanceof Dandelion) {
            newOrganism = new Dandelion(position, this);
        } else if (organism instanceof Guarana) {
            newOrganism = new Guarana(position, this);
        } else if (organism instanceof Wolfberries) {
            newOrganism = new Wolfberries(position, this);
        } else if (organism instanceof PineBorscht) {
            newOrganism = new PineBorscht(position, this);
        }
        addToLivingOrganisms(newOrganism);
    }

    public void newLivingOrganism(String name, Position position) {
        Organism newOrganism = switch (name) {
            case "Wolf" -> new Wolf(position, this);
            case "Sheep" -> new Sheep(position, this);
            case "Fox" -> new Fox(position, this);
            case "Turtle" -> new Turtle(position, this);
            case "Antelope" -> new Antelope(position, this);
            case "Grass" -> new Grass(position, this);
            case "Dandelion" -> new Dandelion(position, this);
            case "Guarana" -> new Guarana(position, this);
            case "Wolfberries" -> new Wolfberries(position, this);
            case "PineBorscht" -> new PineBorscht(position, this);
            default -> null;
        };
        addToLivingOrganisms(newOrganism);
    }

    public void addToLivingOrganisms(Organism newOrganism) {
        livingOrganisms.add(newOrganism);
    }

    public boolean chanceOfBeingTrue(float chance) {
        return Math.random() <= chance;
    }

    private void updateLivingOrganisms(){
        livingOrganisms.removeIf(livingOrganism -> livingOrganism.position == null);
    }

    private void spawnPlayer(){
        Position playerPosition = new Position(sizeX / 2, sizeY / 2);
        player = new Player(playerPosition, this);
        addToLivingOrganisms(player);
    }

    public void addAnnounce(String announce){
        announces.add(announce);
    }

    private void clearAnnounces(){
        announces.clear();
    }

    public void saveGameState(){
        Saver saver = new Saver();
        saver.saveGameState(this);
    }
}
