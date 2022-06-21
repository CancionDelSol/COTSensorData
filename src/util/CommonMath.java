package util;

import java.util.Random;

public class CommonMath {
    //region Fields
    private static Random _rand = new Random();
    //endregion

    //region Constants

    //endregion

    //region Random
    public static int Uniform(int under, int over) {
        return _rand.nextInt(over - under) + under;
    }

    public static double Uniform(double under, double over) {
        return (_rand.nextDouble() * (over - under)) + under;
    }

    public static long Uniform(long under, long over) {
        return _rand.nextLong() % (over - under) + under;
    }
    //endregion
}
