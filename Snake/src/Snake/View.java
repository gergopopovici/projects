package Snake;

import javax.swing.*;
import java.awt.*;

public class View extends JPanel {
    private final Model model;

    public View(Model model) {
        this.model = model;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (model.getGameRunning()) {
            g.setColor(Color.RED);
            g.fillOval(model.getAppleX(), model.getAppleY(), model.getUnitSize(), model.getUnitSize());
            int[] x = model.getX();
            int[] y = model.getY();
            for (int i = 0; i < model.getBodyParts(); ++i) {
                if (i == 0) {
                    g.setColor(Color.green);
                    g.fillRect(x[0], y[0], model.getUnitSize(), model.getUnitSize());
                } else {
                    g.setColor(new Color(3, 70, 34));
                    g.fillRect(x[i], y[i], model.getUnitSize(), model.getUnitSize());
                }
            }
            g.setColor(Color.red);
            g.setFont( new Font("Times New Roman",Font.BOLD, 40));
            FontMetrics metrics = getFontMetrics(g.getFont());
            g.drawString("Score: "+model.getScore(), (model.getScreenWidth()- metrics.stringWidth("Score: "+model.getScore()))/2, g.getFont().getSize());
        }
        else{
            gameOver(g);
        }
    }
    public void gameOver(Graphics g) {
     //   g.setColor(Color.red);
        g.setFont( new Font("Times New Roman",Font.BOLD, 40));
        FontMetrics metrics1 = getFontMetrics(g.getFont());
        g.drawString("Score: "+model.getScore(), (model.getScreenWidth() - metrics1.stringWidth("Score: "+model.getScore()))/2, g.getFont().getSize());
        g.setColor(Color.red);
        g.setFont( new Font("Times New Roman",Font.BOLD, 75));
        FontMetrics metrics2 = getFontMetrics(g.getFont());
        g.drawString("Game Over", (model.getScreenWidth() - metrics2.stringWidth("Game Over"))/2, model.getScreenHeight()/2);
    }
}
