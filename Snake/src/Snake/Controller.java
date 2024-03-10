package Snake;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.*;

import static Snake.HighScoreManager.generateLeaderboard;

public class Controller implements ActionListener, KeyListener {

    private final Model model;
    private final View view;
    private final Timer timer;


    public Controller(Model model, View view) {
        this.model = model;
        this.view = view;
        view.setFocusable(true);
        view.addKeyListener(this);
        timer = new Timer(75, this);
        timer.start();

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (model.getGameRunning()) {
            model.move();
            model.Collision();
            if(!model.getGameRunning()){
                saveHighScore();
            }
            model.appleEaten();
            view.repaint();
        }
    }

    private void saveHighScore() {
        String playerName = JOptionPane.showInputDialog(view, "Game Over! Enter your name:", "Game Over", JOptionPane.PLAIN_MESSAGE);
        HighScoreManager.saveHighScore(playerName, model.getScore());
        MainMenu.displayLeaderBoard();
        System.exit(0);
    }


    public void stopTimer() {
        timer.stop();
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_LEFT, KeyEvent.VK_A:
                if (model.getDirection() != 'R') {
                    model.setDirection('L');
                }
                break;
            case KeyEvent.VK_RIGHT, KeyEvent.VK_D:
                if (model.getDirection() != 'L') {
                    model.setDirection('R');
                }
                break;
            case KeyEvent.VK_UP, KeyEvent.VK_W:
                if (model.getDirection() != 'D') {
                    model.setDirection('U');
                }
                break;
            case KeyEvent.VK_DOWN, KeyEvent.VK_S:
                if (model.getDirection() != 'U') {
                    model.setDirection('D');
                }
                break;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
