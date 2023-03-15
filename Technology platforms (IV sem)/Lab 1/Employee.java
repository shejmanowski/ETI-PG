package Employees;

import java.util.Objects;
import java.util.Set;

public class Employee implements Comparable<Employee>{
    private String name;
    private String jobTitle;
    private String department;
    private int clearanceLevel;
    private int salary;
    Set<Employee> subordinates;

    public Employee(String name, String jobTitle, String department, int clearanceLevel, int salary, Set<Employee> subordinates) {
        this.name = name;
        this.jobTitle = jobTitle;
        this.department = department;
        this.clearanceLevel = clearanceLevel;
        this.salary = salary;
        this.subordinates = subordinates;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getJobTitle() {
        return jobTitle;
    }

    public void setJobTitle(String jobTitle) {
        this.jobTitle = jobTitle;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public int getClearanceLevel() {
        return clearanceLevel;
    }

    public void setClearanceLevel(int clearanceLevel) {
        this.clearanceLevel = clearanceLevel;
    }

    public int getSalary() {
        return salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Employee employee = (Employee) o;
        return clearanceLevel == employee.clearanceLevel && salary == employee.salary && Objects.equals(name, employee.name) && Objects.equals(jobTitle, employee.jobTitle) && Objects.equals(department, employee.department) && Objects.equals(subordinates, employee.subordinates);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, jobTitle, department, clearanceLevel, salary, subordinates);
    }


    @Override
    public String toString() {
        return "-Employee{" +
                "name='" + name + '\'' +
                ", jobTitle='" + jobTitle + '\'' +
                ", department='" + department + '\'' +
                ", clearanceLevel=" + clearanceLevel +
                ", salary=" + salary + "}";
    }

    public void printRecursive(int lvl){
        for(int i = 0; i < lvl; i++){
            System.out.print("-");
        }
        System.out.println(this);
        if(subordinates != null) {
            lvl++;
            for (Employee s : subordinates) {
                s.printRecursive(lvl);
            }
        }
    }

    public int countSubordinates(){
        int subNumber = 0;

        if(subordinates != null) {
            for (Employee s : subordinates) {
                subNumber++;
                subNumber += s.countSubordinates();
            }
        }
        return  subNumber;
    }

    @Override
    public int compareTo(Employee other){

        return name.compareTo(other.name);
    }

}
