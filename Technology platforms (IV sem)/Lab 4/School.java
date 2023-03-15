import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.OneToMany;

import lombok.*;

import java.util.List;

@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@Entity
public class School {

    @Override
    public String toString() {
        return "School{" +
                "name='" + name + '\'' +
                ", influence=" + influence +
                '}';
    }


    @Getter
    @Id
    private String name;

    @Getter
    @Setter
    private int influence;

    @Getter
    @Setter
    @OneToMany(mappedBy = "school", cascade = { CascadeType.REMOVE })
    private List<Wizard> wizards;
}
