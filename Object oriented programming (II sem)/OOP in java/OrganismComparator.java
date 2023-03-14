import java.util.Comparator;

public class OrganismComparator implements Comparator<Organism> {
    @Override
    public int compare(Organism o1, Organism o2) {
        int ret = o2.getInitiative() - o1.getInitiative();
        if (ret == 0) ret = o2.getAge() - o1.getAge();
        return ret;
    }
}
