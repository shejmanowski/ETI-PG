package Employees;

import java.util.*;

public class SubNumberMap {

    public HashMap<String, Integer> makeStatsMap(ArrayList<Employee> employeeList){
        HashMap<String, Integer> statsMap = new HashMap<String, Integer>();

        for(Employee e : employeeList){
            statsMap.put(e.getName(), e.countSubordinates());
        }

        return statsMap;
    }

    public TreeMap<String, Integer> makeStatsMapSorted(ArrayList<Employee> employeeList){
        TreeMap<String, Integer> statsMap = new TreeMap<String, Integer>();

        for(Employee e : employeeList){
            statsMap.put(e.getName(), e.countSubordinates());
        }

        return statsMap;
    }
}
