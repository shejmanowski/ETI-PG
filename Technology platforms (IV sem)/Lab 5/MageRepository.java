import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;

import java.util.Collection;
import java.util.Optional;

@AllArgsConstructor
@NoArgsConstructor
@ToString
@EqualsAndHashCode
public class MageRepository {

    private Collection<Mage> mages;

    public Optional<Mage> find(String name){
        Mage retMage = null;
        if(mages == null){
            return Optional.ofNullable(retMage);
        }
        for(Mage mage : mages){
            if(mage.getName().equals(name)){
                retMage = mage;
                break;
            }
        }
        return Optional.ofNullable(retMage);
    }

    public void delete(String name) throws IllegalArgumentException{
        boolean exist = find(name).isPresent();
        if(!exist) {
            throw new IllegalArgumentException();
        }
        find(name).ifPresent(mage -> mages.remove(mage));
    }

    public void save(Mage mage) throws IllegalArgumentException {
        boolean alreadyExists = find(mage.getName()).isPresent();
        if(alreadyExists){
            throw new IllegalArgumentException();
        }
        mages.add(mage);
    }
}
