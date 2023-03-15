import Employees.ArgsDealer;
import Employees.Employee;
import Employees.SubNumberMap;

import java.util.*;

public class PT_Lab1 { //wszystkie zadania z laboratorium zostały zaimplementowane

    public static void main(String[] args){

        ArgsDealer argsDealer = new ArgsDealer();

        Employee employee1 = new Employee("Bob", "Software Engineer",
                "New York", 2, 5000, null);

        Employee employee2 = new Employee("Robert", "Junior Developer lv2",
                "New York", 3, 2000, null);

        Employee employee3 = new Employee("Emily", "Junior Developer lv4",
                "New York", 7, 4000, null);

        Employee employee4 = new Employee("Stanley", "Junior Developer lv1",
                "New York", 1, 1000, null);

        Set<Employee> sub1 = argsDealer.menageArgs(args);
        sub1.add(employee1);
        sub1.add(employee2);
        sub1.add(employee3);
        sub1.add(employee4);


        Employee employee5 = new Employee("Pam", "Senior Developer lv1",
                "Dallas", 2, 6000, null);

        Employee employee6 = new Employee("Jim", "Junior Developer lv10",
                "Dallas", 2, 5000, null);

        Employee employee7 = new Employee("Kevin", "Junior Developer lv8",
                "Dallas", 2, 8000, null);

        Set<Employee> sub2 = argsDealer.menageArgs(args);
        sub2.add(employee5);
        sub2.add(employee6);
        sub2.add(employee7);

        Employee employee8 = new Employee("Mike", "Senior Developer",
                "Chicago", 3, 5000, sub1);


        Employee employee9 = new Employee("John", "Senior Developer",
                "Berlin", 7, 7000, sub2);

        Set<Employee> sub3 = argsDealer.menageArgs(args);
        sub3.add(employee8);
        sub3.add(employee9);

        Employee employee10 = new Employee("Trevor", "CEO",
                "Los Angeles", 1, 10000, sub3);

        SubNumberMap es = new SubNumberMap();
        Map<String, Integer> statMap;

        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.addAll(sub1);
        employeeList.addAll(sub2);
        employeeList.addAll(sub3);
        employeeList.add(employee10);

        if(args.length == 0){ //if there is no args, then no sort on map
            statMap = new HashMap<>(es.makeStatsMap(employeeList));
        } else { // altSort or naturalSort, then sort on map
            statMap = new TreeMap<>(es.makeStatsMapSorted(employeeList));
        }

        employee10.printRecursive(0);
        System.out.println("\n" + statMap);
    }
}
