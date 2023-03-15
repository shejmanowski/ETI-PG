import lombok.AllArgsConstructor;

@AllArgsConstructor
public class MageController {
    private MageRepository rep;

    public String find(String name) {
        boolean exist = rep.find(name).isPresent();
        if(exist){
            return rep.find(name).toString();
        }
        else{
            return "not found";
        }
    }

    public String delete(String name) {
        try {
            rep.delete(name);
            return "done";
        } catch(IllegalArgumentException iae){
            return "not found";
        }
    }

    public String save(String name, int level) {
        try {
            Mage mageToSave = new Mage(name, level);
            rep.save(mageToSave);
            return "done";
        } catch(IllegalArgumentException iae){
            return "bad request";
        }
    }
}
