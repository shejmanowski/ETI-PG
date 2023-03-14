import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonsPanel extends JPanel implements ActionListener {
    private final int panelWidth = 540;
    private final int panelHeight = 360;
    private JButton loadButton;
    private JButton saveGameState;
    private GameFrame gameFrame;
    private World world;

    public ButtonsPanel(World world, GameFrame gameFrame){
        this.gameFrame = gameFrame;
        this.world = world;
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        setBackground(new Color(100, 100, 100));
        loadButton = new JButton();
        loadButton.setText("LOAD GAME");
        loadButton.setFocusable(false);
        saveGameState = new JButton();
        saveGameState.setText("SAVE GAME");
        saveGameState.setFocusable(false);
        add(loadButton);
        add(saveGameState);
        JButton wolfButton = new JButton();
        wolfButton.setText("WOFL");
        wolfButton.setFocusable(false);
        add(wolfButton);
        JButton turtleButton = new JButton();
        turtleButton.setText("TURTLE");

        add(turtleButton);
        JButton antelopeButton = new JButton();
        antelopeButton.setText("ANTELOPE");

        add(antelopeButton);
        JButton foxButton = new JButton();
        foxButton.setText("FOX");

        add(foxButton);
        JButton sheepButton = new JButton();
        sheepButton.setText("SHEEP");

        add(sheepButton);
        JButton grassButton = new JButton();
        grassButton.setText("GRASS");

        add(grassButton);
        JButton wolfberriesButton = new JButton();
        wolfberriesButton.setText("WOLFBERRIES");

        add(wolfberriesButton);
        JButton pineBorschtButton = new JButton();
        pineBorschtButton.setText("PINE BORSCHT");

        add(pineBorschtButton);
        JButton guaranaButton = new JButton();
        guaranaButton.setText("GUARANA");

        add(guaranaButton);
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==loadButton){
            Loader loader = new Loader();
            gameFrame.changeWorld(loader.loadGameState());
        }
        if(e.getSource()==saveGameState){
            world.saveGameState();
        }
    }
}
