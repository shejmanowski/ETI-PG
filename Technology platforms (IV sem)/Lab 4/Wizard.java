import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.ManyToOne;

import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
@Entity
public class Wizard {

    @Getter
    @Id
    private String name;

    @Getter
    @Setter
    private int level;

    @Getter
    @Setter
    @ManyToOne
    private School school;

}
