import org.junit.Test;
import org.mockito.Mockito;

import java.util.Optional;
import static org.assertj.core.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;

public class MageControllerTest {
    @Test
    public void find_notExistingObject_notFound(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Mockito.when(mr.find("NotExisting")).thenReturn(Optional.empty());
        String result = mc.find("NotExisting");

        assertThat(result).isEqualTo("not found");
    }

    @Test
    public void find_validObject_objectToString(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Optional<Mage> mage = Optional.of(new Mage("validMage", 12));
        Mockito.when(mr.find("validMage")).thenReturn(mage);

        assertThat(mc.find("validMage")).isEqualTo(mage.toString());
    }

    @Test
    public void delete_notExistingObject_notFound(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Mockito.doThrow(new IllegalArgumentException()).when(mr).delete("notExisting");
        String result = mc.delete("notExisting");

        assertThat(result).isEqualTo("not found");
    }

    @Test
    public void delete_validObject_done(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Mockito.doNothing().when(mr).delete("validObject");
        String result = mc.delete("validObject");

        assertThat(result).isEqualTo("done");

    }

    @Test
    public void save_alreadyExistingObject_badRequest(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Mockito.doThrow(new IllegalArgumentException()).when(mr).save(any(Mage.class));
        String result = mc.save("existingMage", 0);

        assertThat(result).isEqualTo("bad request");
    }

    @Test
    public void save_validObject_done(){
        MageRepository mr = Mockito.mock(MageRepository.class);
        MageController mc = new MageController(mr);

        Mockito.doNothing().when(mr).save(new Mage());
        String result = mc.save("validObject", 0);

        assertThat(result).isEqualTo("done");
    }
}
