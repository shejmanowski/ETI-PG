import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import java.util.Scanner;

public class Main {


    public static void main(String[] args) {

        EntityManagerFactory emf = Persistence.createEntityManagerFactory("rpgPu");
        JpaManager jpaM = new JpaManager(emf);
        QueryManager queryManager = new QueryManager(emf);
        Scanner scan = new Scanner(System.in);
        RandomDataGenerator rdg = new RandomDataGenerator(jpaM, emf);
        boolean running = true;

        rdg.createRandomSchools(8);
        rdg.createRandomWizards(20);


        while(running){
            System.out.print("command: ");
            String command = scan.next();
            switch (command) {
                case "add_wizard" -> {
                    System.out.print("Name: ");
                    String newWizardName = scan.next();
                    System.out.print("Level: ");
                    int newWizardLvl = scan.nextInt();
                    System.out.print("School: ");
                    String schoolName = scan.next();
                    School school = jpaM.findSchoolByName(schoolName);
                    Wizard newWizard = new Wizard(newWizardName, newWizardLvl, school);
                    jpaM.add(newWizard);
                }
                case "add_school" -> {
                    System.out.print("Name: ");
                    String newSchoolName = scan.next();
                    System.out.print("Influence: ");
                    int newSchoolInfluence = scan.nextInt();
                    School newSchool = new School(newSchoolName, newSchoolInfluence, null);
                    jpaM.add(newSchool);
                }
                case "delete" -> {
                    System.out.print("Name: ");
                    String recordToDelName = scan.next();
                    Object recordToDel = jpaM.findWizardByName(recordToDelName);
                    if (recordToDel == null) {
                        recordToDel = jpaM.findSchoolByName(recordToDelName);
                    }
                    jpaM.delete(recordToDel);
                    System.out.println(recordToDel + " deleted successfully:)");
                }
                case "show" -> {
                    jpaM.printSchools();
                    jpaM.printWizards();
                }
                case "query1" -> {
                    System.out.print("Min influence: ");
                    int minInfluence = scan.nextInt();
                    System.out.println(queryManager.query1(minInfluence));
                }
                case "query2" -> {
                    System.out.print("School name: ");
                    String querySchoolName = scan.next();
                    System.out.print("Min level: ");
                    int minLvl = scan.nextInt();
                    System.out.println(queryManager.query2(querySchoolName, minLvl));
                }
                case "quit" -> running = false;
            }
        }
    }
}
