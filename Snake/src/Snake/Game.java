package Snake;

import javax.swing.*;
import java.awt.*;
import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;


public class Game extends JFrame {

    public Game() {
        Model model = new Model();
        View view = new View(model);
        Controller controller = new Controller(model, view);

        view.setPreferredSize(new Dimension(model.getScreenWidth(), model.getScreenHeight()));

        this.setTitle("Snake");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);

        this.getContentPane().add(view);

        this.pack();

        this.setLocationRelativeTo(null);

        this.setVisible(true);
        model.startGame();
        try {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File("sound/music.wav"));
            Clip clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            clip.start();
        } catch (UnsupportedAudioFileException | LineUnavailableException | IOException e) {
            System.out.println("IO error");
        }

    }
}

