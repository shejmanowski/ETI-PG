import java.io.Serializable;

public class Announcer implements Serializable {
    public Announcer(){};

    public String death(Organism killed, Organism killer){
        String glue = " killed ";
        if (killed instanceof Plant) glue = " aet ";
        return killer.toString() + glue + killed.toString();
    }

    public String spreading(Organism spreader){
        return spreader.toString() + " spreads";
    }

    public String reproduction(Organism reproducer){
        return reproducer.toString() + " reproduces";
    }

    public String move(Organism mover, Position position){
        return mover.toString() + " hops on " + position.toString();
    }
}
