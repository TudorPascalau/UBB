package model;

import java.util.Objects;

public class Student extends Entity<Integer> implements Comparable<Student> {
    private String nume;
    private float medie;

    public Student(String nume, float medie) {
        this.nume = nume;
        this.medie = medie;
    }

    public String getNume() {
        return nume;
    }

    public float getMedie() {
        return medie;
    }

    @Override
    public String toString() {
        return "Student [nume=" + nume + ", medie=" + medie + "]";
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Float.compare(medie, student.medie) == 0 && Objects.equals(nume, student.nume);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, medie);
    }

    @Override
    public int compareTo(Student o) {
        return this.nume.compareTo(o.nume);
    }
}
