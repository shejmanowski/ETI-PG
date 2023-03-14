import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class AnnouncerPanel extends JPanel {
    private final int panelWidth = 540;
    private final int panelHeight = 360;
    private final World world;

    public AnnouncerPanel(World world){
        this.world = world;
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        this.setBackground(new Color(210, 180, 190));
        JLabel labelText = new JLabel();
        JLabel labelText1 = new JLabel();
        JLabel labelText2 = new JLabel();
        JLabel labelText3 = new JLabel();
        labelText.setText("Wolf kills Fox");
        add(labelText);
        labelText1.setText("Antelope eat Grass");
        add(labelText1);
        labelText2.setText("Dandelion spreads");
        add(labelText2);
        labelText3.setText("Grass spreads");
        add(labelText3);
    }

    public void paint(){
        ArrayList<String> announcesList = world.getAnnounces();
        String[] announces = new String[announcesList.size()];
        announcesList.toArray(announces);
        if(announces.length != 0){
            JList announcesJList = new JList(announces);
            add(announcesJList);
        }
    }
}
