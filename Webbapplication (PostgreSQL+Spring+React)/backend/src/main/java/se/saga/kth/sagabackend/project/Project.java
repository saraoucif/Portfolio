package se.saga.kth.sagabackend.project;

import jakarta.persistence.*;
import java.time.LocalDate;

@Entity
@Table
public class Project {

    @Id
    @SequenceGenerator(
            name = "project_sequence",
            sequenceName = "project_sequence",
            allocationSize = 1
    )
    @GeneratedValue(
            strategy = GenerationType.SEQUENCE,
            generator = "project_sequence"
    )

    private Integer ID;
    private String projectName;
    private String projectManager;
    private String status;
    private LocalDate startDate, goLiveDate;
    private Integer progress;
    private Integer teamSize;
    private String description, notes, clientInformation;
    private boolean milestone1, milestone2, milestone3, milestone4;

    public Project(Integer ID, String projectName, String projectManager, String status, LocalDate startDate, LocalDate goLiveDate,
                   Integer progress, Integer teamSize, String description, String notes, String clientInformation,
                   boolean milestone1, boolean milestone2, boolean milestone3, boolean milestone4) {
        this.ID = ID;
        this.projectName = projectName;
        this.projectManager = projectManager;
        this.status = status;
        this.startDate = startDate;
        this.goLiveDate = goLiveDate;
        this.progress = progress;
        this.teamSize = teamSize;
        this.description = description;
        this.notes = notes;
        this.clientInformation = clientInformation;
        this.milestone1 = milestone1;
        this.milestone2 = milestone2;
        this.milestone3 = milestone3;
        this.milestone4 = milestone4;
    }

    public Project(String projectName, String projectManager, String status, LocalDate startDate, LocalDate goLiveDate,
                   Integer progress, Integer teamSize, String description, String notes, String clientInformation,
                   boolean milestone1, boolean milestone2, boolean milestone3, boolean milestone4) {
        this.projectName = projectName;
        this.projectManager = projectManager;
        this.status = status;
        this.startDate = startDate;
        this.goLiveDate = goLiveDate;
        this.progress = progress;
        this.teamSize = teamSize;
        this.description = description;
        this.notes = notes;
        this.clientInformation = clientInformation;
        this.milestone1 = milestone1;
        this.milestone2 = milestone2;
        this.milestone3 = milestone3;
        this.milestone4 = milestone4;
    }

    public Project() {

    }

    public Integer getID() {
        return ID;
    }

    public String getProjectName() {
        return projectName;
    }

    public String getProjectManager() {
        return projectManager;
    }

    public String getStatus() {
        return status;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public LocalDate getGoLiveDate() {
        return goLiveDate;
    }

    public Integer getProgress() {
        return progress;
    }

    public Integer getTeamSize() {
        return teamSize;
    }

    public String getDescription() {
        return description;
    }

    public String getNotes() {
        return notes;
    }

    public String getClientInformation() {
        return clientInformation;
    }

    public void setID(Integer ID) {
        this.ID = ID;
    }

    public void setProjectName(String projectName) {
        this.projectName = projectName;
    }

    public void setProjectManager(String projectManager) {
        this.projectManager = projectManager;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public void setGoLiveDate(LocalDate goLiveDate) {
        this.goLiveDate = goLiveDate;
    }

    public void setProgress(Integer progress) {
        this.progress = progress;
    }

    public void setTeamSize(Integer teamSize) {
        this.teamSize = teamSize;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }

    public void setClientInformation(String clientInformation) {
        this.clientInformation = clientInformation;
    }

    public boolean getMilestone1() {
        return milestone1;
    }

    public void setMilestone1(boolean milestone1) {
        this.milestone1 = milestone1;
    }

    public boolean getMilestone2() {
        return milestone2;
    }

    public void setMilestone2(boolean milestone2) {
        this.milestone2 = milestone2;
    }

    public boolean getMilestone3() {
        return milestone3;
    }

    public void setMilestone3(boolean milestone3) {
        this.milestone3 = milestone3;
    }

    public boolean getMilestone4() {
        return milestone4;
    }

    public void setMilestone4(boolean milestone4) {
        this.milestone4 = milestone4;
    }

    @Override
    public String toString() {
        return "Project{" +
                "ID=" + ID +
                ", projectName='" + projectName + '\'' +
                ", projectManager='" + projectManager + '\'' +
                ", status='" + status + '\'' +
                ", startDate=" + startDate +
                ", goLiveDate=" + goLiveDate +
                ", progress=" + progress +
                ", teamSize=" + teamSize +
                ", description='" + description + '\'' +
                ", notes='" + notes + '\'' +
                ", clientInformation='" + clientInformation + '\'' +
                ", milestone1=" + milestone1 +
                ", milestone2=" + milestone2 +
                ", milestone3=" + milestone3 +
                ", milestone4=" + milestone4 +
                '}';
    }
}

