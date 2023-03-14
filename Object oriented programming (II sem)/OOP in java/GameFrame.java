import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class GameFrame extends JFrame implements KeyListener {
    private World world;
    private Player player;
    public GameFrame() {
        world = new World(20, 20, false);
        player = world.getPlayer();
        setTitle("PO Project 2 - Szymon Hejmanowski 184487");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        add(new MainPanel(world, this));
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
        setResizable(false);
        addKeyListener(this);
    }

    @Override
    public void keyTyped(KeyEvent e) {
        if(e.getKeyChar() == 'w') player.setDesiredDirection(0);
        if(e.getKeyChar() == 'd') player.setDesiredDirection(1);
        if(e.getKeyChar() == 's') player.setDesiredDirection(2);
        if(e.getKeyChar() == 'a') player.setDesiredDirection(3);
        if(e.getKeyChar() == 'e') player.setDesiredDirection(4);
        if(e.getKeyChar() == 'z') player.setDesiredDirection(5);
        if(e.getKeyChar() == 'q') {
            player.activateAbility();
            return;
        }
        if(e.getKeyChar() == 'p') {
            world.saveGameState();
            return;
        }
        world.nextRound();
        repaint();
    }

    @Override
    public void keyPressed(KeyEvent e) {
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }

    public void newWorld(){
        world = new World(20, 20, false);
        player = world.getPlayer();
    }

    public void changeWorld(World world){
        this.world = world;
        this.player = world.getPlayer();
        repaint();
    }
}
