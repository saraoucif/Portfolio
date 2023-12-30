package se.saga.kth.sagabackend.project;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.time.LocalDate;

@Configuration
public class ProjectConfig {

    @Bean
    CommandLineRunner commandLineRunner(ProjectRepository projectRepository) {
        return args -> {
            Project p1 = new Project(
                    1,
                    "SAGA",
                    "me",
                    "running",
                    LocalDate.of(2021, 4,13),
                    LocalDate.of(2021, 5, 13),
                    100,
                    4,
                    "desc",
                    "notes",
                    "clientinfo",
                    false,
                    false,
                    false,
                    false);

            Project p2 = new Project(
                    2,
                    "PROJECT 2",
                    "me",
                    "running",
                    LocalDate.of(2023, 4,13),
                    LocalDate.of(2023, 6, 17),
                    100,
                    4,
                    "desc",
                    "notes",
                    "clientinfo",
                    false,
                    false,
                    false,
                    false);
        };
    }
}
