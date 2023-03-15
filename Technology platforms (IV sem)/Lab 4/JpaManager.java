import lombok.NoArgsConstructor;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import java.util.List;

@NoArgsConstructor
public class JpaManager {

    EntityManagerFactory emf;

    public JpaManager(EntityManagerFactory emf){
        this.emf = emf;
    }

    public void add(Object entity){
        EntityManager em = emf.createEntityManager();
        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        em.persist(entity);
        transaction.commit();
        em.close();
    }

    public void delete(Object entity){
        EntityManager em = emf.createEntityManager();
        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        em.remove(em.merge(entity));
        transaction.commit();
        em.close();
    }

    public School findSchoolByName(String schoolName) {
        EntityManager em = emf.createEntityManager();
        School schoolFound = em.find(School.class, schoolName);
        em.close();
        return schoolFound;
    }



    public Wizard findWizardByName(String wizardName) {
        EntityManager em = emf.createEntityManager();
        Wizard wizardFound = em.find(Wizard.class, wizardName);
        em.close();
        return wizardFound;
    }

    public void printWizards(){
        System.out.println("Wizard table:");
        EntityManager em = emf.createEntityManager();
        String queryString = "SELECT w FROM Wizard w";
        Query query = em.createQuery(queryString, Wizard.class);
        List<Wizard> wizards = query.getResultList();
        System.out.println(wizards);
        em.close();
    }

    public void printSchools(){
        System.out.println("School table:");
        EntityManager em = emf.createEntityManager();
        String queryString = "SELECT s FROM School s";
        Query query = em.createQuery(queryString, School.class);
        List<School> schools = query.getResultList();
        System.out.println(schools);
        em.close();
    }
}
