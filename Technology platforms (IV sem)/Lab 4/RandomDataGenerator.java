import javax.persistence.EntityManagerFactory;
import java.util.*;

public class RandomDataGenerator {

    private final ArrayList<String> wizardNamesList = new ArrayList<>();
    private final ArrayList<String> schoolNamesList = new ArrayList<>();
    private final JpaManager jpaM;
    private final Random random;
    private final QueryManager queryManager;

    public RandomDataGenerator(JpaManager jpaM, EntityManagerFactory emf){
        Collections.addAll(wizardNamesList, "Liam", "Noah", "Oliver", "Elijah", "William", "James", "Benjamin", "Lucas", "Henry",
                "Olivia", "Emma", "Ava", "Charlotte", "Sophia", "Amelia", "Isabella", "Mia", "Evelyn", "Harper", "Alexander", "Adam");
        Collections.addAll(schoolNamesList, "TheBiggest", "MediumOne", "TheOneWithoutDoors", "TheOneWithSmallWindows", "TheBlackOne", "TheOneForFemales", "TheMostKnown", "TheOneForPsychos");
        this.jpaM = jpaM;
        random = new Random();
        queryManager = new QueryManager(emf);
    }

    public void createRandomSchools(int number){
        for(int i = 0; i < number; i++){
            int randomIndex = random.nextInt(schoolNamesList.size());
            String name = schoolNamesList.get(randomIndex);
            schoolNamesList.remove(randomIndex);
            int influence = random.nextInt(10);
            School school = new School(name, influence, null);
            jpaM.add(school);
        }
    }

    public void createRandomWizards(int number){
        for(int i = 0; i < number; i++){
            int randomIndex =random.nextInt( wizardNamesList.size());
            String name = wizardNamesList.get(randomIndex);
            wizardNamesList.remove(randomIndex);
            int level = random.nextInt(20);
            List<String> schoolNames = (List<String>) queryManager.query1(0);
            String schoolName = schoolNames.get(random.nextInt(schoolNames.size()));
            School school = jpaM.findSchoolByName(schoolName);
            Wizard wizard = new Wizard(name, level, school);
            jpaM.add(wizard);
        }
    }
}
