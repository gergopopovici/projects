package Snake;
import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class HighScoreManager {
    private static final String HIGH_SCORE_FILE = "highscores.dat";

    public static void saveHighScore(String playerName, int score) {
        List<HighScore> highScores = loadHighScores();
        HighScore newHighScore = new HighScore(playerName, score);
        highScores.add(newHighScore);
        highScores.sort(Comparator.comparingInt(HighScore::getScore).reversed());

        try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(HIGH_SCORE_FILE))) {
            outputStream.writeObject(highScores);
            System.out.println("High score saved successfully!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static List<HighScore> loadHighScores() {
        List<HighScore> highScores = new ArrayList<>();

        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(HIGH_SCORE_FILE))) {
            highScores = (List<HighScore>) inputStream.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("No high scores found");
        }

        return highScores;
    }

    public static int calculateTotalScore() {
        List<HighScore> highScores = loadHighScores();

        return highScores.stream()
                .mapToInt(HighScore::getScore)
                .sum();
    }

    public static List<HighScore> generateLeaderboard(int threshold) {
        List<HighScore> highScores = loadHighScores();

        return highScores.stream()
                .filter(score -> score.getScore() > threshold)
                .collect(Collectors.toList());
    }
}
