import javax.swing.*;
import java.awt.*;

public class MainPanel extends JPanel {
    public MainPanel(World world, GameFrame gameFrame){
        setPreferredSize(new Dimension(1080, 720));
        setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0)); // can add gaps
        setBackground(new Color(45, 55, 60));
        add(new BoardPanel(world));
        add(new HudPanel(world, gameFrame));
    }
}
