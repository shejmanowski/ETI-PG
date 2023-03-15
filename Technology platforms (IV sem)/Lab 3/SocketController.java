public interface SocketController {

    String prepareResponse(String uri);

    boolean accepts(String uri);
}
