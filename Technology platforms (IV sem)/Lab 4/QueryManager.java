import lombok.AllArgsConstructor;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import java.util.List;

@AllArgsConstructor
public class QueryManager {

    EntityManagerFactory emf;

    public List<String> query1(int minInfluence){
        EntityManager em = emf.createEntityManager();
        String queryString = "SELECT s.name FROM School s WHERE s.influence > :minInfluence";
        Query query = em.createQuery(queryString, String.class);
        query.setParameter("minInfluence", minInfluence);
        return (List<String>) query.getResultList();
    }

    public List<String> query2(String schoolName, int minLvl){
        EntityManager em = emf.createEntityManager();
        String queryString = "SELECT w.name FROM Wizard w WHERE w.level > :minLvl AND w.school.name LIKE :schoolName";
        Query query = em.createQuery(queryString, String.class);
        query.setParameter("minLvl", minLvl).setParameter("schoolName", schoolName);
        List<String> ret = (List<String>) query.getResultList();
        ret.sort(null);
        return ret;
    }

}
