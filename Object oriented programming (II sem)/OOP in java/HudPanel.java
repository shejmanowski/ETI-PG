import javax.swing.*;
import java.awt.*;

public class HudPanel extends JPanel {
    public HudPanel(World world, GameFrame gameFrame){
        int panelWidth = 540;
        int panelHeight = 720;
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
        add(new AnnouncerPanel(world));
        add(new ButtonsPanel(world, gameFrame));
    }
}
