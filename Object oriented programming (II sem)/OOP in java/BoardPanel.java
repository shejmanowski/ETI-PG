import javax.swing.*;
import java.awt.*;

import static java.lang.Math.*;

public class BoardPanel extends JPanel {
    private final World world;
    private final int panelWidth = 540;
    private final int panelHeight = 720;
    private final int gridSize;
    private final int centerOffset;

    public BoardPanel(World world) {
        this.world = world;
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        setBackground(new Color(40, 45, 55));
        gridSize = calculateGridSize();
        centerOffset = gridSize / 2;
    }

    public void paint(Graphics g) {
        Graphics2D g2D = (Graphics2D) g;
        if (!world.getHexMode()) {
            Position startAt = calculateDrawingStartingPosition();
            for (int i = startAt.getX(); i < world.getSizeX() * gridSize + startAt.getX(); i += gridSize) {
                for (int j = startAt.getY(); j < world.getSizeY() * gridSize + startAt.getY(); j += gridSize) {
                    Position inGamePosition = new Position(i / gridSize, j / gridSize);
                    Color fieldColor = new Color(255, 255, 255);
                    if (!world.isEmpty(inGamePosition)) fieldColor = world.getOrganism(inGamePosition).getColor();
                    g2D.setColor(fieldColor);
                    g2D.fillRect(i, j, gridSize, gridSize);
                }
            }
        } else {
            Position startAt = calculateDrawingStartingPosition();
            for (int i = startAt.getX(); i < world.getSizeX() * gridSize + startAt.getX(); i += gridSize) {
                for (int j = startAt.getY(); j < world.getSizeY() * gridSize + startAt.getY(); j += gridSize) {
                    Position inGamePosition = new Position(i / gridSize, j / gridSize);
                    Color fieldColor = new Color(255, 255, 255);
                    if (!world.isEmpty(inGamePosition)) fieldColor = world.getOrganism(inGamePosition).getColor();
                    g2D.setColor(fieldColor);
                    g2D.fillRect(i, j, gridSize, gridSize);
                }
            }
        }
    }

    public int calculateGridSize() {
        if(world.getHexMode()) return Math.min(panelWidth / 2 / world.getSizeX(), panelHeight / 2 / world.getSizeY());
        else return Math.min(panelWidth / world.getSizeX(), panelHeight / world.getSizeY());
    }


    public int[] calculatePointsX(Position center){
        int [] hexPositionsX = new int[6];
        for(int i = 0; i < 6; i++) {
            var angle_deg = 60 * i - 30;
            var angle_rad = PI / 180 * angle_deg;
            hexPositionsX[i] = (int) (center.getX() + 100 * cos(angle_rad));
        }
        return hexPositionsX;
    }

    public int[] calculatePointsY(Position center){
        int [] hexPositionsY = new int[6];
        for(int i = 0; i < 6; i++) {
            var angle_deg = 60 * i - 30;
            var angle_rad = PI / 180 * angle_deg;
            hexPositionsY[i] = (int) (center.getY() + 100 * sin(angle_rad));
        }
        return hexPositionsY;
    }

    public Position calculateDrawingStartingPosition() {
        return new Position(panelWidth / 2 - (gridSize * world.getSizeX()) / 2,
                panelHeight / 2 - (gridSize * world.getSizeY()) / 2);
    }

    public Position calculateFieldCenter(int x, int y) {
        return new Position(x * gridSize + centerOffset, y * gridSize + centerOffset);
    }
}
