package Snake;


import javax.swing.*;
import java.awt.*;
import java.util.List;

import static Snake.HighScoreManager.generateLeaderboard;


public class MainMenu extends JFrame {
    public MainMenu() {
        setVisible(true);
        setTitle("Snake-Main Menu");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Font buttonFont = new Font("Times New Roman",Font.BOLD,24);
        JButton start = new JButton("Start Game");
        start.setFont(buttonFont);
        JButton help = new JButton("Help");
        JButton average = new JButton("Average Score");
        JButton exit = new JButton("Exit");
        JButton leaderBoard = new JButton("Leader Board");
        help.setFont(buttonFont);
        start.setFont(buttonFont);
        exit.setFont(buttonFont);
        average.setFont(buttonFont);
        leaderBoard.setFont(buttonFont);
        start.addActionListener(e -> {
            Game game = new Game();
            game.setVisible(true);
            dispose();
        });
        exit.addActionListener(e -> System.exit(0));
        help.addActionListener(e -> {
            String helpMessage = "Snake Game Help\n\n" +
                    "Controls:\n" +
                    "   - Use arrow keys (Up, Down, Left, Right) to control the snake.\n" +
                    "   - Press 'W' 'A' 'D' 'S' keys as alternative controls for UP,Left,Right and Down\n\n" +
                    "Objective:\n" +
                    "   - Eat the apples to grow the snake and increase your score.\n" +
                    "   - Avoid collisions with the snake's own body and the game boundaries.\n" +
                    "   - The game ends when the snake collides with itself or the boundaries.\n\n" +
                    "Have fun playing Snake!";
            JOptionPane.showMessageDialog(this, helpMessage);
        });
        leaderBoard.addActionListener(e -> displayLeaderBoard());
        average.addActionListener(e -> {
            double averageScore = calculateAverageScore();
            JOptionPane.showMessageDialog(this, "Average Score: " + averageScore, "Average Score", JOptionPane.INFORMATION_MESSAGE);
        });
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 1));
        panel.add(start);
        panel.add(leaderBoard);
        panel.add(average);
        panel.add(help);
        panel.add(exit);
        add(panel);
        setSize(450, 450);
        setLocationRelativeTo(null);
    }

    public static void displayLeaderBoard() {
        int threshold = 0;
        List<HighScore> leaderboard = generateLeaderboard(threshold);

        StringBuilder leaderboardText = new StringBuilder("Leaderboard:\n");

        for (int i = 0; i < leaderboard.size(); i++) {
            HighScore score = leaderboard.get(i);
            leaderboardText.append((i + 1)).append(" ").append("\t").append(score.getName()).append(" ").append(score.getScore()).append("\n");
        }

        JOptionPane.showMessageDialog(null, leaderboardText.toString(), "Leaderboard", JOptionPane.INFORMATION_MESSAGE);
    }

    public double calculateAverageScore() {
        List<HighScore> highScores = generateLeaderboard(0);

        return highScores.stream()
                .mapToInt(HighScore::getScore)
                .average()
                .orElse(0.0);
    }

    public static void main(String[] args) {
        new MainMenu();
    }
}
