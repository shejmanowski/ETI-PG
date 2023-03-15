import org.junit.Test;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;
import static org.assertj.core.api.Assertions.*;

public class MageRepositoryTest {

    @Test
    public void find_notExistingObject_true(){
        MageRepository mr = new MageRepository(null);
        Optional<Mage> mage = mr.find("Example");
        assertThat(mage.isEmpty()).isEqualTo(true);
    }

    @Test
    public void find_existingObject_true(){
        Collection<Mage> mages = new ArrayList<Mage>();
        Mage mage = new Mage("Mage1", 15);
        mages.add(mage);
        MageRepository mr = new MageRepository(mages);
        assertThat(mr.find("Mage1").isPresent()).isEqualTo(true);
    }

    @Test(expected = IllegalArgumentException.class)
    public void delete_notExistingObject_exceptionThrow(){
        MageRepository mr = new MageRepository(null);
        mr.delete("NotExistingObject");
    }

    @Test(expected = IllegalArgumentException.class)
    public void save_alreadyExistingObject_exceptionThrow(){
        Collection<Mage> mages = new ArrayList<Mage>();
        Mage existingMage = new Mage("Mage1", 15);
        mages.add(existingMage);
        MageRepository mr = new MageRepository(mages);
        Mage newMage = new Mage("Mage1", 11);
        mr.save(newMage);
    }

}
