package Snake;

import javax.sound.sampled.*;
import java.io.File;
import java.util.Random;

public class Model {
    private static final int unitSize = 50;
    private static final int SCREEN_WIDTH = 1000;
    private static final int SCREEN_HEIGHT = 600;
    private Clip clip;
    private final int[] x;
    private final int[] y;
    private int score;
    private int appleX;
    private int appleY;
    private int bodyParts;
    private char direction;
    private boolean gameRunning;
    private final Random random;

    public Model() {
        x = new int[SCREEN_WIDTH * SCREEN_HEIGHT / unitSize];
        y = new int[SCREEN_HEIGHT * SCREEN_WIDTH / unitSize];
        random = new Random();
        gameInit();
    }

    public void gameInit() {
        bodyParts = 4;
        score = 0;
        direction = 'R';
        gameRunning = true;
        newApple();
    }

    public int getAppleX() {
        return appleX;
    }

    public int getAppleY() {
        return appleY;
    }

    public int getBodyParts() {
        return bodyParts;
    }

    public int[] getX() {
        return x;
    }

    public int[] getY() {
        return y;
    }

    public int getScore() {
        return score;
    }

    public char getDirection() {
        return direction;
    }

    public void setDirection(char direction) {
        this.direction = direction;
    }

    public int getScreenWidth() {
        return SCREEN_WIDTH;
    }

    public int getScreenHeight() {
        return SCREEN_HEIGHT;
    }

    public int getUnitSize() {
        return unitSize;
    }

    public boolean getGameRunning() {
        return gameRunning;
    }

    public void newApple() {
        if (score != 0) {
            playSound("sound/bite.wav");
        }
        appleX = random.nextInt((int) (SCREEN_WIDTH / unitSize - 1)) * unitSize;
        appleY = random.nextInt((int) (SCREEN_HEIGHT / unitSize - 1)) * unitSize;
    }

    private void playSound(String fileName) {
        try {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(fileName).getAbsoluteFile());
            Clip clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            clip.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void move() {
        for (int i = bodyParts; i > 0; i--) {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }

        switch (direction) {
            case 'U':
                y[0] = y[0] - unitSize;
                break;
            case 'D':
                y[0] = y[0] + unitSize;
                break;
            case 'L':
                x[0] = x[0] - unitSize;
                break;
            case 'R':
                x[0] = x[0] + unitSize;
                break;
        }
    }

    public void Collision() {
        if (x[0] < 0 || x[0] >= SCREEN_WIDTH || y[0] < 0 || y[0] >= SCREEN_HEIGHT) {
            playSound("sound/crash.wav");
            gameRunning = false;
            return;
        }

        for (int i = 1; i < bodyParts; i++) {
            if (x[0] == x[i] && y[0] == y[i]) {
                playSound("sound/crash.wav");
                gameRunning = false;
                return;
            }
        }
    }


    public void appleEaten() {
        if ((x[0] == appleX) && (y[0] == appleY)) {
            score++;
            bodyParts++;
            newApple();
        }
    }

    public void startGame() {
        gameInit();
    }
}
