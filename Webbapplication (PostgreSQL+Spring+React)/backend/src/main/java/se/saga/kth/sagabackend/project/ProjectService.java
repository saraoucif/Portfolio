package se.saga.kth.sagabackend.project;

import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class ProjectService {

    private final ProjectRepository projectRepository;

    @Autowired
    public ProjectService(ProjectRepository projectRepository) {
        this.projectRepository = projectRepository;
    }

    public List<Project> getProjects(){
        return projectRepository.findAll();
    }

    public Project getProject(Integer id){
        Optional<Project> result = projectRepository.findById(id);
        if(result.isPresent()) {
            return result.get();
        } else {
            return null;
        }

    }

    public List<Project> getProjects(Object o){
        return projectRepository.findAll();
    }

    public Project addNewProject(Project project) {
        if(project.getTeamSize() == null) project.setTeamSize(0);
        if(project.getDescription() == null) project.setDescription("");
        if(project.getNotes() == null) project.setNotes("");
        if(project.getClientInformation() == null) project.setClientInformation("");

        project.setMilestone1(project.getMilestone1());
        project.setMilestone2(project.getMilestone2());
        project.setMilestone3(project.getMilestone3());
        project.setMilestone4(project.getMilestone4());

        Project savedProject = projectRepository.save(project);
        return savedProject;
    }

    public void deleteProject(Integer projectID) {
        boolean exists = projectRepository.existsById(projectID);
        if(!exists) throw new IllegalStateException("project with id " + projectID + " does not exist");
        projectRepository.deleteById(projectID);
    }

    @Transactional
    public void updateProject(Project updatedProject) {
        Optional<Project> projectOptional = projectRepository.findById(updatedProject.getID());
        if(projectOptional.isEmpty()){
            throw new IllegalStateException("project with id "+updatedProject.getID()+" does not exist");
        }
        projectOptional.get().setProjectName(updatedProject.getProjectName());
        projectOptional.get().setProjectManager(updatedProject.getProjectManager());
        projectOptional.get().setStatus(updatedProject.getStatus());
        projectOptional.get().setStartDate(updatedProject.getStartDate());
        projectOptional.get().setGoLiveDate(updatedProject.getGoLiveDate());
        projectOptional.get().setProgress(updatedProject.getProgress());
        projectOptional.get().setClientInformation(updatedProject.getClientInformation());
        projectOptional.get().setNotes(updatedProject.getNotes());
        projectOptional.get().setTeamSize(updatedProject.getTeamSize());
        projectOptional.get().setDescription(updatedProject.getDescription());

        projectOptional.get().setMilestone1(updatedProject.getMilestone1());
        projectOptional.get().setMilestone2(updatedProject.getMilestone2());
        projectOptional.get().setMilestone3(updatedProject.getMilestone3());
        projectOptional.get().setMilestone4(updatedProject.getMilestone4());
    }
}
