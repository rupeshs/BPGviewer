#include "qbetterportablegraphics.h"

static void png_write_data (png_structp png_ptr, png_bytep data,
                            png_size_t length)
{
    FILE *f;
    int ret;

    f = (FILE*)png_get_io_ptr(png_ptr);
    ret = fwrite(data, 1, length, f);
    if (ret != length)
        png_error(png_ptr, "PNG Write Error");
}

QBetterPortableGraphics::QBetterPortableGraphics(QObject *parent) :
    QObject(parent)
{

}
bool QBetterPortableGraphics::openFile(QString filePath)
{
    _isBPG=false;
    _qfileName=filePath;
    _fileName=_qfileName.toStdString().c_str();
    _mapInfo.clear();
    ReadHeader();
}
bool QBetterPortableGraphics::ReadHeader()
{
    int show_extensions=1;
    uint8_t *buf;
    int buf_len, ret, buf_len_max;
    FILE *f;
    BPGImageInfo p_s, *p = &p_s;
    BPGExtensionData *first_md, *md;
    static const char *format_str[6] = {
        "Gray",
        "4:2:0",
        "4:2:2",
        "4:4:4",
        "4:2:0_video",
        "4:2:2_video",
    };
    static const char *color_space_str[BPG_CS_COUNT] = {
        "YCbCr",
        "RGB",
        "YCgCo",
        "YCbCr_BT709",
        "YCbCr_BT2020",
    };
    static const char *extension_tag_str[] = {
        "Unknown",
        "EXIF",
        "ICC profile",
        "XMP",
        "Thumbnail",
    };

    f = fopen(_fileName, "rb");
    if (!f) {
        qDebug ("Could not open file");
        return false;
    }

    if (show_extensions) {
        fseek(f, 0, SEEK_END);
        buf_len_max = ftell(f);
        fseek(f, 0, SEEK_SET);
    } else {
        /* if no extension are shown, just need the header */
        buf_len_max = BPG_DECODER_INFO_BUF_SIZE;
    }

    buf = (uint8_t*)malloc(buf_len_max);
    buf_len = fread(buf, 1, buf_len_max, f);

    ret = bpg_decoder_get_info_from_buf(p, show_extensions ? &first_md : NULL,
                                        buf, buf_len);
    free(buf);
    fclose(f);
    if (ret < 0) {
        qDebug( "Not a BPG image\n");
        _isBPG=false;
        return false;
    }

    if(p->width>0)
    {_width= p->width;
        _mapInfo.insert("Width",QString::number(p->width));
    }

    if(p->height>0)
    {_height= p->height;
        _mapInfo.insert("Height",QString::number(p->height));
    }
    _bpgInfo=p;

    qDebug("size=%dx%d color_space=%s",
           p->width, p->height,
           p->format == BPG_FORMAT_GRAY ? "Gray" : color_space_str[p->color_space]);
    _mapInfo.insert("Color space", p->format == BPG_FORMAT_GRAY ? "Gray" : color_space_str[p->color_space]);
    if (p->has_w_plane) {
        qDebug(" w_plane=%d", p->has_w_plane);
    }
    if (p->has_alpha) {
        qDebug(" alpha=%d premul=%d",
               p->has_alpha, p->premultiplied_alpha);
        _mapInfo.insert("Has alpha",QString::number(p->has_alpha));
        _mapInfo.insert("Premultiplied Alpha",QString::number(p->premultiplied_alpha));

    }
    qDebug(" format=%s limited_range=%d bit_depth=%d\n",
           format_str[p->format],
           p->limited_range,
           p->bit_depth);
    _mapInfo.insert("limited Range",QString::number( p->limited_range));
    _mapInfo.insert("Format",QString(format_str[p->format]));
    _mapInfo.insert("Bit depth",QString::number(p->bit_depth));

    if (first_md) {
        const char *tag_name;
        qDebug("Extension data:\n");
        for(md = first_md; md != NULL; md = md->next) {
            if (md->tag <= 4)
                tag_name = extension_tag_str[md->tag];
            else
                tag_name = extension_tag_str[0];
            qDebug("  tag=%d (%s) length=%d\n",
                   md->tag, tag_name, md->buf_len);
        }
        bpg_decoder_free_extension_data(first_md);
    }

    return true;
}

void QBetterPortableGraphics::decodeBpg(){

    int bit_depth=8;
    FILE *f;
    BPGDecoderContext *img;
    uint8_t *buf;

    int buf_len;
    f = fopen(_qfileName.toStdString().c_str(), "rb");
    if (!f) {
        qDebug( )<<"Could not open file "<<QString::fromAscii(_fileName);
        return;
    }

    fseek(f, 0, SEEK_END);
    buf_len = ftell(f);
    fseek(f, 0, SEEK_SET);

    buf = (uint8_t*)malloc(buf_len);
    if (fread(buf, 1, buf_len, f) != buf_len) {
        qDebug("Error while reading file");
        return;
    }

    fclose(f);

    img = bpg_decoder_open();

    if (bpg_decoder_decode(img, buf, buf_len) < 0) {
        qDebug("Could not decode image");

    }
    //bpgImage.fromData(QbyteArry(img))

    free(buf);


    BPGImageInfo img_info_s, *img_info = &img_info_s;

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep row_pointer;
    int y, color_type, bpp;
    BPGDecoderOutputFormat out_fmt;

    if (bit_depth != 8 && bit_depth != 16) {
        fprintf(stderr, "Only bit_depth = 8 or 16 are supported for PNG output\n");
        exit(1);
    }

    bpg_decoder_get_info(img, img_info);

    QString outFile=QDesktopServices::storageLocation(QDesktopServices::TempLocation)+QString("/bpgviewerimg.png");
    qDebug()<<outFile;
    f = fopen(outFile.toAscii(), "wb");
    if (!f) {
        qDebug( "I/O error\n");

    }

    png_ptr = png_create_write_struct_2(PNG_LIBPNG_VER_STRING,
                                        NULL,
                                        NULL,  /* error */
                                        NULL, /* warning */
                                        NULL,
                                        NULL,
                                        NULL);
    info_ptr = png_create_info_struct(png_ptr);
    png_set_write_fn(png_ptr, (png_voidp)f, &png_write_data, NULL);

    if (setjmp(png_jmpbuf(png_ptr)) != 0) {
        qDebug( "PNG write error");
        exit(1);
    }

    if (img_info->has_alpha)
        color_type = PNG_COLOR_TYPE_RGB_ALPHA;
    else
        color_type = PNG_COLOR_TYPE_RGB;

    png_set_IHDR(png_ptr, info_ptr, img_info->width, img_info->height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
    if (bit_depth == 16) {
        png_set_swap(png_ptr);
    }
#endif

    if (bit_depth == 16) {
        if (img_info->has_alpha)
            out_fmt = BPG_OUTPUT_FORMAT_RGBA64;
        else
            out_fmt = BPG_OUTPUT_FORMAT_RGB48;
    } else {
        if (img_info->has_alpha)
            out_fmt = BPG_OUTPUT_FORMAT_RGBA32;
        else
            out_fmt = BPG_OUTPUT_FORMAT_RGB24;
    }

    bpg_decoder_start(img, out_fmt);

    bpp = (3 + img_info->has_alpha) * (bit_depth / 8);
    row_pointer = (png_bytep)png_malloc(png_ptr, img_info->width * bpp);
    for (y = 0; y < img_info->height; y++) {
        bpg_decoder_get_line(img, row_pointer);
        png_write_row(png_ptr, row_pointer);
    }
    png_free(png_ptr, row_pointer);

    png_write_end(png_ptr, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(f);
    bpg_decoder_close(img);

    emit imageready(QDesktopServices::storageLocation(QDesktopServices::TempLocation)+"/bpgviewerimg.png");

}
