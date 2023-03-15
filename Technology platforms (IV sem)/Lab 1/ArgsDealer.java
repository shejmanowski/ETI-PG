package Employees;

import java.util.*;

public class ArgsDealer {

    public Set<Employee> menageArgs(String[] arg) {

        if (arg.length == 0) {
            return new HashSet<>();
        } else if (arg[0].equals("naturalSort")) {
            return new TreeSet<>();
        } else if (arg[0].equals("altSort")) {
            return new TreeSet<>(new SalarySort());
        }
        return null;
    }

    /*public Map<String, Integer> manageArgsMap(String[] arg){

        SubNumberMap subNumberMap = new SubNumberMap();

        if (arg.length == 0) {
            return
        } else {
            return new TreeMap<>();
        }
    }*/
}
