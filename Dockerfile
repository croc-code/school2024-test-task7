FROM eclipse-temurin:21-jre-alpine
LABEL authors="Артемий"
COPY commits.txt /opt/app/commits.txt
COPY ./target/*.jar /opt/app/krok_camp.jar
WORKDIR /opt/app
ENTRYPOINT ["java", "-jar", "krok_camp.jar"]